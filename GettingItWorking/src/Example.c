//
//  Example.cpp
//  Example
//

#include "Example.h"

ExampleClass::ExampleClass() {
	m_iValue = 0;
}

int ExampleClass::GetValue() {
	return m_iValue;
}

void ExampleClass::DoSomething() {
	m_iValue = 3;
}