import SwiftUI

struct FrequencyView: View {
    let numberSamples = 500
    let wav: (Double) -> Double
    let period: Double
    let numberCycles = 501.0
    let color: Color

    var body: some View {
        GeometryReader { geometry in
            let center = geometry.size.center
            Path { path in
                path.move(to: CGPoint(x: 0.0, y: center.y))
                for i in 0..<numberSamples {
                    let x = Double(i)*geometry.size.width/(Double(numberSamples))
                    let y = (wav(Double(i)/period*numberCycles/Double(numberSamples))*200.0) + center.y
                    path.addLine(to: CGPoint(x: x, y: y))
                }

            }.stroke(color, lineWidth: 1)
        }
    }
}

struct FrequencyView_Previews: PreviewProvider {
    static var previews: some View {
        FrequencyView(wav: sin, period: 2 * Double.pi, color: .blue)
    }
}
