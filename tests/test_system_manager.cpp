#include "catch.hpp"
#include "core/system.h"
#include "core/system_manager.h"
#include <vector>

class TestSystemResults
{
public:
	std::vector<uint32_t> m_testDeleted;
	std::vector<uint32_t> m_preInitCalled;
	std::vector<uint32_t> m_initCalled;
	std::vector<uint32_t> m_postInitCalled;
	std::vector<uint32_t> m_preShutdownCalled;
	std::vector<uint32_t> m_shutdownCalled;
	std::vector<uint32_t> m_postShutdownCalled;
	std::vector<uint32_t> m_tickCalled;
};

template<int TestIndex>
class TestSystem : public Core::ISystem
{
public:
	TestSystem(TestSystemResults& results) : m_results(results) {}
	virtual ~TestSystem() { m_results.m_testDeleted.push_back(TestIndex); }

	virtual bool PreInit(Core::ISystemEnumerator& systemEnumerator) { m_results.m_preInitCalled.push_back(TestIndex); return true; }
	virtual bool Initialise() { m_results.m_initCalled.push_back(TestIndex);	return true; }
	virtual bool PostInit() { m_results.m_postInitCalled.push_back(TestIndex);	return true; }

	virtual bool Tick() { m_results.m_tickCalled.push_back(TestIndex); return true; }

	virtual void PreShutdown()	{ m_results.m_preShutdownCalled.push_back(TestIndex); }
	virtual void Shutdown()		{ m_results.m_shutdownCalled.push_back(TestIndex); }
	virtual void PostShutdown() { m_results.m_postShutdownCalled.push_back(TestIndex); }

private:
	TestSystemResults& m_results;
};

TEST_CASE("System Manager functionality", "[Core::SystemManager]")
{
	SECTION("System registration")
	{
		Core::SystemManager sysManager;
		TestSystemResults testResults;
		auto testSys = new TestSystem<0>(testResults);
		sysManager.RegisterSystem("TestSystem0", testSys);
		REQUIRE(sysManager.GetSystem("TestSystem0") == testSys);
		REQUIRE(sysManager.GetSystem("Unknown") == nullptr);
	}

	SECTION("Tests deleted on shutdown")
	{
		TestSystemResults testResults;
		{
			Core::SystemManager sysManager;
			sysManager.RegisterSystem("Sys0", new TestSystem<0>(testResults));
			sysManager.RegisterSystem("Sys1", new TestSystem<1>(testResults));
		}
		REQUIRE(testResults.m_testDeleted.size() == 2);
		REQUIRE(testResults.m_testDeleted[0] == 0);
		REQUIRE(testResults.m_testDeleted[1] == 1);
	}

	SECTION("Tests Initialise in correct order")
	{
		Core::SystemManager sysManager;
		TestSystemResults testResults;
		sysManager.RegisterSystem("Sys0", new TestSystem<0>(testResults));
		sysManager.RegisterSystem("Sys1", new TestSystem<1>(testResults));
		sysManager.RegisterSystem("Sys2", new TestSystem<2>(testResults));
		REQUIRE(sysManager.Initialise() == true);

		REQUIRE(testResults.m_preInitCalled.size() == 3);
		REQUIRE(testResults.m_preInitCalled[0] == 0);
		REQUIRE(testResults.m_preInitCalled[1] == 1);
		REQUIRE(testResults.m_preInitCalled[2] == 2);

		REQUIRE(testResults.m_initCalled.size() == 3);
		REQUIRE(testResults.m_initCalled[0] == 0);
		REQUIRE(testResults.m_initCalled[1] == 1);
		REQUIRE(testResults.m_initCalled[2] == 2);

		REQUIRE(testResults.m_postInitCalled.size() == 3);
		REQUIRE(testResults.m_postInitCalled[0] == 0);
		REQUIRE(testResults.m_postInitCalled[1] == 1);
		REQUIRE(testResults.m_postInitCalled[2] == 2);
	}

	SECTION("Tests Tick in correct order")
	{
		Core::SystemManager sysManager;
		TestSystemResults testResults;
		sysManager.RegisterSystem("Sys0", new TestSystem<0>(testResults));
		sysManager.RegisterSystem("Sys1", new TestSystem<1>(testResults));
		REQUIRE(sysManager.Initialise() == true);
		REQUIRE(sysManager.Tick() == true);

		REQUIRE(testResults.m_tickCalled.size() == 2);
		REQUIRE(testResults.m_tickCalled[0] == 0);
		REQUIRE(testResults.m_tickCalled[1] == 1);
	}

	SECTION("Tests Shutdown in correct order")
	{
		Core::SystemManager sysManager;
		TestSystemResults testResults;
		sysManager.RegisterSystem("Sys0", new TestSystem<0>(testResults));
		sysManager.RegisterSystem("Sys1", new TestSystem<1>(testResults));
		REQUIRE(sysManager.Initialise() == true);
		REQUIRE(sysManager.Tick() == true);
		sysManager.Shutdown();

		REQUIRE(testResults.m_preShutdownCalled.size() == 2);
		REQUIRE(testResults.m_preShutdownCalled[0] == 0);
		REQUIRE(testResults.m_preShutdownCalled[1] == 1);

		REQUIRE(testResults.m_shutdownCalled.size() == 2);
		REQUIRE(testResults.m_shutdownCalled[0] == 0);
		REQUIRE(testResults.m_shutdownCalled[1] == 1);

		REQUIRE(testResults.m_postShutdownCalled.size() == 2);
		REQUIRE(testResults.m_postShutdownCalled[0] == 0);
		REQUIRE(testResults.m_postShutdownCalled[1] == 1);
	}

	SECTION("PreInit failure reported")
	{
		Core::SystemManager sysManager;
		class FailPreInit : public Core::ISystem
		{
			virtual bool PreInit(Core::ISystemEnumerator& systemEnumerator) { return false; }
		};
		sysManager.RegisterSystem("Fail", new FailPreInit);
		REQUIRE(sysManager.Initialise() == false);
	}

	SECTION("Init failure reported")
	{
		Core::SystemManager sysManager;
		class FailInit : public Core::ISystem
		{
			virtual bool Initialise() { return false; }
		};
		sysManager.RegisterSystem("Fail", new FailInit);
		REQUIRE(sysManager.Initialise() == false);
	}

	SECTION("PostInit failure reported")
	{
		Core::SystemManager sysManager;
		class FailPostInit : public Core::ISystem
		{
			virtual bool PostInit() { return false; }
		};
		sysManager.RegisterSystem("Fail", new FailPostInit);
		REQUIRE(sysManager.Initialise() == false);
	}

	SECTION("Tick failure reported")
	{
		Core::SystemManager sysManager;
		class FailTick : public Core::ISystem
		{
			virtual bool Tick() { return false; }
		};
		sysManager.RegisterSystem("Fail", new FailTick);
		REQUIRE(sysManager.Initialise() == true);
		REQUIRE(sysManager.Tick() == false);
	}
}