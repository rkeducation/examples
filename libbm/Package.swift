// swift-tools-version:5.7
import PackageDescription

let package = Package(
	name: "libbm",
	targets: [
		.executableTarget(
			name: "libbm",
			path: ".",
			sources: ["main.c", "src"],
			publicHeadersPath: "src/include",
			cSettings: [
				.unsafeFlags(["-std=c11"]) // C11 standard
			]
		)
	]
)
