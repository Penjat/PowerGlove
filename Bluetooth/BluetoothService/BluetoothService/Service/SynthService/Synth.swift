import AVFoundation
import Combine

class Synth: ObservableObject {
    @Published var wavCap = false
    @Published var isPlaying = false
    @Published var wav: (Double) -> Double = sin
    var bag = Set<AnyCancellable>()
    static var amplitude: Double = 1

    typealias Signal = (_ time: Double) -> Double

    public var volume: Float {
        set {
            audioEngine.mainMixerNode.outputVolume = newValue
        }
        get {
            audioEngine.mainMixerNode.outputVolume
        }
    }

    public func startPlaying() {
        volume = 0.05
    }

    public func stopPlaying() {
        volume = 0
    }

    func pressedKey(_ keyNumber: Int, down: Bool) {
        print("pressed \(keyNumber)")
        if down {
            let halfStepsFromA4 = (keyNumber - 69)
            let a = 1.059463094359
            startPlaying()
            return
        }
        stopPlaying()
    }

    private var audioEngine: AVAudioEngine
    private lazy var sourceNode = AVAudioSourceNode { _, _, frameCount, audioBufferList in
        let ablPointer = UnsafeMutableAudioBufferListPointer(audioBufferList)

        let period: Float = 1.0

        for frame in 0..<Int(frameCount) {
            let sampleVal = self.signal(Double(self.time))
            self.time += self.deltaTime

            if self.wavCap {
                self.time = fmod(self.time, period)
            }

            for buffer in ablPointer {
                let buf: UnsafeMutableBufferPointer<Float> = UnsafeMutableBufferPointer(buffer)
                buf[frame] = Float(sampleVal)
            }
        }

        return noErr
    }

    private var time: Float = 0
    private let sampleRate: Double
    private let deltaTime: Float
    private var signal: Signal = { time in
        let theta = Double(2.0 * Double.pi * 440.0 * time)
        return amplitude * sin(theta)
    }

    // MARK: Init



    init() {
        audioEngine = AVAudioEngine()

        let mainMixer = audioEngine.mainMixerNode
        let outputNode = audioEngine.outputNode
        let format = outputNode.inputFormat(forBus: 0)

        sampleRate = format.sampleRate
        deltaTime = 1 / Float(sampleRate)

        let inputFormat = AVAudioFormat(commonFormat: format.commonFormat,
                                        sampleRate: format.sampleRate,
                                        channels: 1,
                                        interleaved: format.isInterleaved)

        audioEngine.attach(sourceNode)
        audioEngine.connect(sourceNode, to: mainMixer, format: inputFormat)
        audioEngine.connect(mainMixer, to: outputNode, format: nil)
        mainMixer.outputVolume = 0

        do {
            try audioEngine.start()
        } catch {
            print("Could not start engine: \(error.localizedDescription)")
        }

        $wav.sink { wav in
            self.signal = { [weak self] time in
//                let theta = Double(2.0 * Float.pi * frequency * time)
                return Synth.amplitude * (self?.wav(Double(time)) ?? 0.0)/2
            }
        }.store(in: &bag)

    }

    // MARK: Public Functions

    public func setWaveformTo(_ signal: @escaping Signal) {
        self.signal = signal
    }

}

