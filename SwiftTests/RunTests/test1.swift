//
//  test1.swift
//  Examples
//
//  Created by Ramesh on 16/01/25.
//

import Testing
import LibNet

@Suite("")
struct TestCases1 {
	@Test func example1() throws {
		// example test case
		#expect(BYTE_ORDER == LITTLE_ENDIAN)
	}
}
