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
		.package(url: "https://github.com/hummingbird-project/hummingbird", from: "2.6.0"),
		.package(url: "https://github.com/apple/swift-argument-parser", from: "1.5.0"),
	],
    targets: [
        // The Swift executable target
        .executableTarget(
            name: "Run",
			dependencies: ["LibNet", "LibTCP"],
            path: "Sources/Run",
			swiftSettings: [.interoperabilityMode(.Cxx)]
        ),
		.systemLibrary(
			name: "LibCurl",
			path: "src/curl",
			providers: [
				.apt(["libcurl4-openssl-dev"]),
				.brew(["curl"])
			]
		),
        // The C++ library target for tensors
        .target(
            name: "LibNet",
            dependencies: [],
            path: "src/net",
            publicHeadersPath: "include",
            cxxSettings: [
                .headerSearchPath("include"),
                .define("USE_CPP_LIB")
            ]
        ),
        // The C++ library target for tcp
        .target(
            name: "LibTCP",
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
            path: "SwiftTests"
        )
    ],
    cxxLanguageStandard: .cxx17
)
