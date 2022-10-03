#include "modc.h"
#include "test/test.h"

TEST_F(modc, proto) {
    TEST_LOG("Testing modc proto..\n");
    EXPECT_EQ(0, modc_proto());
}
