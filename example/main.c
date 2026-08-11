#include <miunte.h>

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
    MIUNTE_EXPECT(testable != 0, "lp0 on fire");

    MIUNTE_PASS();
}
MiunteResult test2() {
    MIUNTE_EXPECT(testable == 0, "lp0 on fire");

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
