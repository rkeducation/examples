//
//  run.swift
//  examples
//
//  Created by Ramesh on 15/01/25.
//

import LibNet
import api

debugPrint("Starting the worker ... ")



let bytes : [UInt8] = [0xFF, 0xAB, 0x0F, 0x23, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF]
let packet = IPPacket(bytes)
print("Bytes = \(bytes.map { String($0) }.joined(separator: " "))")







debugPrint("Stopping the worker ... ")
