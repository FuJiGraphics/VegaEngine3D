#pragma once

namespace vega {
	class System;

	/*
	* @brief Ŭ���̾�Ʈ���� �������Ͽ� �ý����� �����մϴ�.
	* @return System*: ������ �ý����� �ּ�
	*/
	System* CreateSystem();
}

extern vega::System* vega::CreateSystem();

int main(int argc, char** argv);