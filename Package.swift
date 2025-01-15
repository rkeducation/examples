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
            exclude: ["main.cpp"],
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
            exclude: ["main.cpp"],
            publicHeadersPath: "include",
            cxxSettings: [
                .headerSearchPath("include"),
                .define("USE_CPP_LIB"),
                .unsafeFlags([
                    "-I/opt/homebrew/Cellar/openssl@3/3.4.0/include"
                ], .when(platforms: [.macOS]))
            ],
            linkerSettings: [
                .linkedLibrary("ssl"),
                .linkedLibrary("crypto"),
                .unsafeFlags(["-L/opt/homebrew/Cellar/openssl@3/3.4.0/lib"], .when(platforms: [.macOS])),
                .unsafeFlags(["-I/opt/homebrew/Cellar/openssl@3/3.4.0/include"], .when(platforms: [.macOS]))
            ]
        ),
        // Unit test target (optional)
        .testTarget(
            name: "RunTests",
            dependencies: ["Run"],
            path: "tests/RunTests"
        )
    ],
    cxxLanguageStandard: .cxx20
)
