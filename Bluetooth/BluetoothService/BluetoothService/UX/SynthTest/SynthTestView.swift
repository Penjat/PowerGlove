import SwiftUI

struct SynthTestView: View {
    @StateObject var viewModel: SynthTestViewModel
    var body: some View {
        VStack {
            ZStack {
                FrequencyView(wav: viewModel.pitch.waveForm(_:), period: viewModel.pitch.frequency, color: .orange).id(viewModel.rotation).frame(height: 300)
                PitchArcView(pitchNames: Note.noteNames, selectedNote: viewModel.currentPitch?.noteNumber ?? 69, lowerBound: SynthTestViewModel.Constants.noteLowerBound, upperBound: SynthTestViewModel.Constants.noteUpperBound)
            }
            Text("frequency: \(viewModel.pitch.frequency)")
            Text("modulation amount: \(viewModel.pitch.modulationAmount)")
            Text("modulation frequency: \(viewModel.pitch.modulationFrequency)")

            Group {
                Picker("wave picker", selection: $viewModel.wavType) {
                    ForEach(WaveType.allCases, id: \.self) { waveType in
                        Text(waveType.rawValue)
                    }
                }.pickerStyle(SegmentedPickerStyle())

                Picker("phase wave picker", selection: $viewModel.phaseModWavType) {
                    ForEach(WaveType.allCases, id: \.self) { waveType in
                        Text(waveType.rawValue)
                    }
                }.pickerStyle(SegmentedPickerStyle())

                Picker("frequency wave picker", selection: $viewModel.frequencyModWavType) {
                    ForEach(WaveType.allCases, id: \.self) { waveType in
                        Text(waveType.rawValue)
                    }
                }.pickerStyle(SegmentedPickerStyle())

            }

            Group {

                Slider(value: $viewModel.finger0)
                Slider(value: $viewModel.finger1)
                Slider(value: $viewModel.finger2)
                Slider(value: $viewModel.finger3)

            }
            HStack {
                LetterButtonView(color: .red, text: "A", size: 60, isPressed: viewModel.pressedA)
                LetterButtonView(color: .yellow, text: "B", size: 60, isPressed: viewModel.pressedB)
                LetterButtonView(color: .green, text: "C", size: 60, isPressed: viewModel.pressedC)
            }
        }.padding(40)
    }

    var possibleNotes: [String] {
        []
    }
}
