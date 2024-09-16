import Foundation
import Combine
import SwiftUI

class GloveSynthViewModel: ObservableObject {
    enum Constants {
        static let notesLowerBound = 60.0
        static let notesUpperBound = 100.0
        static let upSwell = 0.1
        static let downSwell = 0.1
    }

    let volumeMax = 0.0
    let upSwell = 0.1
    let downSwell = 0.1

    let timer = Timer.publish(every: 0.1, on: .main, in: .default)
        .autoconnect()

    @Published var gloveState: PowerGloveDataObject?

    @Published var selectedNote: (note: Int?, isHeld: Bool) = (note: nil, false)

    var bag = Set<AnyCancellable>()

    @Published var wavType: WaveType = .sin
    @Published var phaseModWavType: WaveType = .sin
    @Published var frequencyModWavType: WaveType = .sin

    let pitch = Pitch()

    init(synth: Synth, gloveService: GloveDataService) {
        synth.wav = pitch.waveForm(_:)
        synth.startPlaying()

        gloveService.$gloveState.assign(to: &$gloveState)

        $gloveState.sink { [weak self] gloveData in
            guard let gloveData else {
                return
            }
            self?.process(gloveData: gloveData)
        }
        .store(in: &bag)

        $wavType.sink { [weak self] waveType in
            self?.pitch.wav = waveType.data.wav
        }.store(in: &bag)

        $phaseModWavType.sink { [weak self] wavType in
            self?.pitch.phaseModWav = wavType.data.wav
        }.store(in: &bag)

        $frequencyModWavType.sink { [weak self] wavType in
            self?.pitch.frequncyModWave = wavType.data.wav
        }.store(in: &bag)
    }

    func process(gloveData: PowerGloveDataObject) {
        if gloveData.fingerSensor1 < 200 {

            if selectedNote.note == nil || selectedNote.isHeld == false {
                selectedNote =  (note: Int(Note.mapValue(Double(gloveData.gyroX), 80, 200, GloveSynthViewModel.Constants.notesLowerBound, GloveSynthViewModel.Constants.notesUpperBound)), isHeld: true)
                if let note = selectedNote.note, let frequency = Note.noteInfo(for:  note)?.frequency {
                    pitch.frequency = frequency
                }
            }
        } else {

            if selectedNote.isHeld == true {
                selectedNote = (note: selectedNote.note, isHeld: false)
            }
        }

        pitch.volume = Note.mapValue(Double(gloveData.fingerSensor1), 40, 200, 1, 0.0)

        pitch.modulationAmount = Note.mapValue(Double(gloveData.fingerSensor3), 20, 200, 0.1, 0.0)

        pitch.phaseModulationAmount = Note.mapValue(Double(gloveData.gyroY), 20, 150, -Double.pi, Double.pi)
        pitch.modulationFrequency = Note.mapValue(Double(gloveData.fingerSensor2), 20, 200.0, 16, 1)
    }
}
