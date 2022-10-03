#include "modc.h"
#include "test/test.h"

TEST_F(modc, Mock) {
    TEST_LOG("Testing modc Mock..\n");
    EXPECT_EQ(42, modc_Mock());
}
