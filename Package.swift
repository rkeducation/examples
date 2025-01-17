// swift-tools-version:6.0

import PackageDescription

let package = Package(
    name: "Examples",
    platforms: [
        .macOS(.v14),
        .iOS(.v16)
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
		.target(
			name: "api",
			dependencies: [
				.product(name: "Hummingbird", package: "hummingbird"),
				.product(name: "HummingbirdHTTP2", package: "hummingbird"),
				.product(name: "ArgumentParser", package: "swift-argument-parser"),
			]
		),
        // The Swift executable target
        .executableTarget(
            name: "Run",
			dependencies: ["LibNet", "LibTCP", "api"],
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
				.headerSearchPath("include"), // Relative path for your project's headers
				.define("USE_CPP_LIB"),
				.unsafeFlags([
					"-I/opt/homebrew/Cellar/openssl@3/3.4.0/include" // Absolute path for OpenSSL headers
				])
			],
			linkerSettings: [
				.linkedLibrary("ssl"),
				.linkedLibrary("crypto"),
				.linkedLibrary("c++"), // Explicitly link C++ standard library
				.linkedLibrary("pthread"), // Threading support
				.unsafeFlags([
					"-L/opt/homebrew/Cellar/openssl@3/3.4.0/lib" // Absolute path for OpenSSL libraries
				])
			]
		),
        // Unit test target (optional)
        .testTarget(
            name: "RunTests",
            dependencies: ["api", "LibNet"],
            path: "SwiftTests",
			swiftSettings: [.interoperabilityMode(.Cxx)]
        )
    ],
    cxxLanguageStandard: .cxx17
)
