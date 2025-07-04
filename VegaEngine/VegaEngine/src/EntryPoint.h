#pragma once

namespace vega {
	class System;

	/*
	* @brief 클라이언트에서 재정의하여 시스템을 생성합니다.
	* @return System*: 생성한 시스템의 주소
	*/
	System* CreateSystem();
}

extern vega::System* vega::CreateSystem();

int main(int argc, char** argv);