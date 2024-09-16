import SwiftUI

struct GloveSynthView: View {
    @StateObject var viewModel: GloveSynthViewModel
    var body: some View {
        ZStack {
            VStack {
                ZStack {
                    FrequencyView(wav: viewModel.pitch.waveForm(_:), period: viewModel.pitch.frequency, color: .orange)

                    PitchArcView(pitchNames: Note.noteNames, selectedNote: currentNote, lowerBound: Int(GloveSynthViewModel.Constants.notesLowerBound), upperBound: Int(GloveSynthViewModel.Constants.notesUpperBound))
                }

                Spacer()
                Text("selected pitch \(viewModel.selectedNote.note ?? 0)")
                Text("modulation frequency \(viewModel.pitch.modulationFrequency)")
                Text("modulation amount \(viewModel.pitch.modulationAmount)")
                Text("phase modulation amount \(viewModel.pitch.phaseModulationAmount)")
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
                PowerGloveStatusView(gloveState: gloveState).opacity(isConnected ? 1.0 : 0.6)

            }

            if !isConnected {
                Text("Not connected...")
            }
        }
    }

    var isConnected: Bool {
        viewModel.gloveState != nil
    }

    var gloveState: PowerGloveDataObject {
        return viewModel.gloveState ?? defaultGloveState
    }

    var currentNote: Int {
        return Int(Note.mapValue(Double(viewModel.gloveState?.gyroX ?? 0), 80, 200, GloveSynthViewModel.Constants.notesLowerBound, GloveSynthViewModel.Constants.notesUpperBound))
    }

    var defaultGloveState: PowerGloveDataObject {
        PowerGloveDataObject(
            fingerSensor1: 255,
            fingerSensor2: 255,
            fingerSensor3: 255,
            button1State: false,
            button2State: false,
            button3State: false,
            gyroX: 0,
            gyroY: 0,
            gyroZ: 0,
            accelX: 0,
            accelY: 0,
            accelZ: 0)
    }
}
