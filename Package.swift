// swift-tools-version:6.0

import PackageDescription

let package = Package(
    name: "Examples",
    platforms: [
        .macOS(.v10_15),
        .iOS(.v13)
    ],
    products: [
        // Define the Swift executable
        .executable(
            name: "Run",
            targets: ["Run"]
        )
    ],
    dependencies: [
        // Add any external dependencies here
    ],
    targets: [
        // The Swift executable target
        .executableTarget(
            name: "Run",
            dependencies: ["tensorlib", "tcplib"],
            path: "Sources/Run"
        ),
        // The C++ library target for tensors
        .target(
            name: "tensorlib",
            dependencies: [],
            path: "src/tensors",
            publicHeadersPath: "include",
            cxxSettings: [
                .headerSearchPath("include"),
                .define("USE_CPP_LIB")
            ]
        ),
        // The C++ library target for tcp
        .target(
            name: "tcplib",
            dependencies: [],
            path: "src/tcp",
            publicHeadersPath: "include",
            cxxSettings: [
                .headerSearchPath("include"),
                .define("USE_CPP_LIB"),
                .unsafeFlags([
                    "-stdlib=libc++",
                    "-I/opt/homebrew/Cellar/openssl@3/3.4.0/include"
                ], .when(platforms: [.macOS]))
            ],
            linkerSettings: [
                .linkedLibrary("ssl"),
                .linkedLibrary("crypto"),
                .unsafeFlags([
                    "-lc++", // Explicitly link the C++ standard library
                    "-lpthread", // Link pthread for threading support
                    "-L/opt/homebrew/Cellar/openssl@3/3.4.0/lib",
                    "-I/opt/homebrew/Cellar/openssl@3/3.4.0/include"
                ], .when(platforms: [.macOS])),
            ]
        ),
        // Unit test target (optional)
        .testTarget(
            name: "RunTests",
            dependencies: ["Run"],
            path: "tests"
        )
    ],
    cxxLanguageStandard: .cxx17
)
