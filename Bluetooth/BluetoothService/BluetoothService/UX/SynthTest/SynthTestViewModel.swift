import Foundation
import Combine

class SynthTestViewModel: ObservableObject {
    enum Constants {
        static let noteLowerBound = 60
        static let noteUpperBound = 88
        static let upSwell = 0.1
        static let downSwell = 0.1
    }
    var bag = Set<AnyCancellable>()

    let timer = Timer.publish(every: 0.1, on: .main, in: .default)
        .autoconnect()

    @Published var pressedA = false
    @Published var pressedB = false
    @Published var pressedC = false

    @Published var finger0 = 0.0
    @Published var finger1 = 0.0
    @Published var finger2 = 0.0
    @Published var finger3 = 0.0

    @Published var rotation = 0.0

    @Published var currentPitch: PitchInfo?
    @Published var wavType: WaveType = .sin
    @Published var phaseModWavType: WaveType = .sin
    @Published var frequencyModWavType: WaveType = .sin

    let pitch = Pitch()

    init(synth: Synth, motionService: MotionService) {
        synth.wav = pitch.waveForm(_:)//waveForm(_:)
        synth.startPlaying()

        motionService.positionPublisher.sink { [weak self] positionData in

            guard let self else {
                return
            }

            self.rotation = atan2(positionData.gravity.x, -positionData.gravity.y)
            self.currentPitch = self.currentPitch(input: self.rotation)
        }.store(in: &bag)

        $wavType.sink { [weak self] waveType in
            self?.pitch.wav = waveType.data.wav
        }.store(in: &bag)

        $phaseModWavType.sink { [weak self] wavType in
            self?.pitch.phaseModWav = wavType.data.wav
        }.store(in: &bag)

        $frequencyModWavType.sink { [weak self] wavType in
            self?.pitch.frequncyModWave = wavType.data.wav
        }.store(in: &bag)

        $finger0.sink { [weak self] newValue in
            self?.pitch.volume = newValue
        }.store(in: &bag)

        $finger1.sink { [weak self] newValue in
            self?.pitch.modulationAmount = Note.mapValue(newValue, 0.0, 1.0, 0.0, 0.2)
        }.store(in: &bag)

        $finger2.sink { [weak self] newValue in
            self?.pitch.modulationFrequency = Note.mapValue(newValue, 0.0, 1.0, 0.1, 16)
        }.store(in: &bag)

        $finger3.sink { [weak self] newValue in
            self?.pitch.phaseModulationAmount = Note.mapValue(newValue, 0.0, 1.0, -Double.pi, Double.pi)
        }.store(in: &bag)
    }

    var volume: Double {
        Note.mapValue(finger0, 0, 1, 0, 1)
    }

    func currentPitch(input: Double) -> PitchInfo? {
        Note.pitchInfo(inputLowerBound: -1.6, inputUpperBound: 1.6, outputLowerBound: Constants.noteLowerBound, outputUpperBound: Constants.noteUpperBound, inputValue: input)
    }
}
