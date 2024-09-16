import Foundation

enum WaveType: String, CaseIterable {
    case sin
    case triangle
    case square
    case saw
    case noise

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
        case .noise:
            return Data(wav: noise(_:))
        }
    }
}
