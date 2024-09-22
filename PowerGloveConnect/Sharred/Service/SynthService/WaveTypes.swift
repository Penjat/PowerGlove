import Foundation

enum WaveType: String, CaseIterable {
    case sin
    case triangle
    case square
    case saw
    case whiteNoise

    struct Data {
    let wav: (Double) -> (Double)
    }

    var data: WaveType.Data {
        switch self {
        case .sin:
            return Data(wav: sin(_:))
        case .triangle:
            return Data(wav: triangleWave(_:))
        case .square:
            return Data(wav: squareWave(_:))
        case .saw:
            return Data(wav: sawWave(_:))
        case .whiteNoise:
            return Data(wav: noise(_:))
        }
    }
}
