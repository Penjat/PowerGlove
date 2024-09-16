import Foundation
import Combine

// Pitch is an object with various parameters that can be controlled
// it outputs a waveform
// does this need to be observable?

class Pitch: ObservableObject {
    @Published var wav: (Double) -> (Double) = sin
    @Published var phaseModWav: (Double) -> (Double) = sin
    @Published var frequncyModWave: (Double) -> (Double) = sin
    @Published var volume = 0.0
    @Published var frequency = 540.0
    @Published var modulationAmount = 0.0
    @Published var modulationFrequency = 1.0
    @Published var phaseModulationAmount = 0.0

    func waveForm(_ input: Double) -> Double {
        let phaseModulation = phaseModulationAmount * phaseModWav(2.0 * Double.pi * modulationFrequency * input)

        let modulatedFrequency = frequency + modulationAmount * frequncyModWave(2.0 * Double.pi * modulationFrequency * input + phaseModulation)

        return wav(2.0 * Double.pi * modulatedFrequency * input) * volume
    }
}
