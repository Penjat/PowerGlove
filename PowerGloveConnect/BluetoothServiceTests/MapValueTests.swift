import XCTest

class MapValueTests: XCTestCase {

    func testMapValueWithinBounds() {
        // Test a value within bounds (inputValue = 0.5)
        let mappedValue = Note.mapValue(0.5, 0.0, 1.0, 60.0, 72.0)
        XCTAssertEqual(mappedValue, 66.0, accuracy: 0.01)
    }

    func testMapValueLowerBound() {
        // Test the lower bound (inputValue = 0.0)
        let mappedValue = Note.mapValue(0.0, 0.0, 1.0, 60.0, 72.0)
        XCTAssertEqual(mappedValue, 60.0, accuracy: 0.01)
    }

    func testMapValueUpperBound() {
        // Test the upper bound (inputValue = 1.0)
        let mappedValue = Note.mapValue(1.0, 0.0, 1.0, 60.0, 72.0)
        XCTAssertEqual(mappedValue, 72.0, accuracy: 0.01)
    }

    func testMapValueOutsideBounds() {
        // Test a value outside bounds (inputValue = -1.0)
        let mappedValue = Note.mapValue(-1.0, 0.0, 1.0, 60.0, 72.0)
        XCTAssertEqual(mappedValue, 60.0, accuracy: 0.01)
    }

    func testMapReverseDirection() {
        // Test a value outside bounds (inputValue = -1.0)
        let mappedValue1 = Note.mapValue(1.0, -1.0, 1.0, 1.0, -1.0)
        XCTAssertEqual(mappedValue1, -1.0, accuracy: 0.01)

        let mappedValue2 = Note.mapValue(0, 0, 255, 1.0, -1.0)
        XCTAssertEqual(mappedValue2, 1.0, accuracy: 0.01)

        let mappedValue3 = Note.mapValue(255, 0, 255, 1.0, -1.0)
        XCTAssertEqual(mappedValue3, -1.0, accuracy: 0.01)
    }

    func testMapValueWithReversedRange() {
            // Define input and output range
            let inputMin = 0.0
            let inputMax = 100.0
            let outputMin = 1.0  // The lowest value in the reversed range
            let outputMax = 0.0  // The highest value in the reversed range

            // Test cases with various input values
            let testCases: [(inputValue: Double, expectedOutput: Double)] = [
                (25.0, 0.75),   // Expected output is calculated as (25 - 0) * (0 - 1) / (100 - 0) + 1
                (50.0, 0.5),    // Expected output is calculated as (50 - 0) * (0 - 1) / (100 - 0) + 1
                (75.0, 0.25),   // Expected output is calculated as (75 - 0) * (0 - 1) / (100 - 0) + 1
                (0.0, 1.0),     // Expected output is the highest value in the reversed range
                (100.0, 0.0),   // Expected output is the lowest value in the reversed range
            ]

            for testCase in testCases {
                let inputValue = testCase.inputValue
                let expectedOutput = testCase.expectedOutput

                // Call the mapValue function
                let actualOutput = Note.mapValue(inputValue, inputMin, inputMax, outputMin, outputMax)

                // Assert that the actual output matches the expected output
                XCTAssertEqual(actualOutput, expectedOutput, accuracy: 0.001) // Use a small delta for floating-point comparisons
            }
        }

}


