#include "pch.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include "FakeMediaElementAdapter.h"
#include "../AvLib/MEAvLibImpl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Sematena::AvLib;
using std::shared_ptr;

namespace AvLib_Test
{
    TEST_CLASS(MEAvLibTest)
    {
    public:
		shared_ptr<FakeMediaElementAdapter> _fakeAdapter;
		shared_ptr<MEAvLibImpl> _libImpl;

		TEST_METHOD_INITIALIZE(TestSetup)
		{
			_fakeAdapter.reset( new FakeMediaElementAdapter() );
			_libImpl.reset( new MEAvLibImpl( _fakeAdapter ) );
		}

        TEST_METHOD(OnPlay_CallsAdapter)
        {
            Assert::IsFalse( _fakeAdapter->PlayCalled );
			_libImpl->Play();
			Assert::IsTrue( _fakeAdapter->PlayCalled );
        }

		TEST_METHOD(OnStop_CallsAdapter)
        {
            Assert::IsFalse( _fakeAdapter->StopCalled );
			_libImpl->Stop();
			Assert::IsTrue( _fakeAdapter->StopCalled );
        }
    };
}