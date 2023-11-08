#pragma once
#include <regex>

using namespace std;

//class RegexManager {
//	// implement map in phase 3
//	regex* patterns = nullptr;
//	string* names = nullptr;
//
//	int noPatterns = 0;
//
//public:
//
//	RegexManager() {
//
//	}
//
//	void addPattern(string pattern, string name) {
//		this->patterns[this->noPatterns] = pattern;
//		this->names[this->noPatterns] = name;
//
//		this->noPatterns += 1;
//	}
//
//	regex getPattern(string name) {
//		for (int i = 0; i < this->noPatterns; i++) {
//			if (name == this->names[i]) {
//				return this->patterns[i];
//			}
//		}
//	}
//
//	RegexManager(RegexManager& table) {
//		
//	}
//
//	~RegexManager() {
//		delete[] patterns;
//		delete[] names;
//	}
//};