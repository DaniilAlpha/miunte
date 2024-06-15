#include "../miunte.h"

int testable = 0;

MiunteResult setup() {
    testable = 1;

    MIUNTE_PASS();
}

MiunteResult teardown() {
    testable = 0;

    MIUNTE_PASS();
}

MiunteResult test1() {
    MIUNTE_EXPECT(testable != 0, "do not fail");

    MIUNTE_PASS();
}
MiunteResult test2() {
    MIUNTE_EXPECT(testable == 0, "fails");

    MIUNTE_PASS();
}

int main() {
    MIUNTE_RUN(
        setup,
        teardown,
        {
            test1,
            test2,
        }
    );
}
