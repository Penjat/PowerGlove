import SwiftUI

struct ContentView: View {
    @EnvironmentObject var appState: AppState
    var body: some View {
        HStack {
            GloveStatusView(viewModel: gloveStatusViewModel)
        }
    }

    var gloveStatusViewModel: GloveStatusViewModel {
        GloveStatusViewModel(gloveService: appState.gloveDataService)
    }
}

#Preview {
    ContentView()
}
