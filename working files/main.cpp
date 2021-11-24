#include "func.h"
#include "trit.h"


using namespace std;
using custom::Unknown;
using custom::True;
using custom::False;
using custom::Trit;
using custom::TritsetTest;



TEST(Round_test, equal) {
    EXPECT_EQ(3, custom::round_up(5,2));
    EXPECT_EQ(4, custom::round_up(10,3));
    EXPECT_EQ(7, custom::round_up(40,6));
    EXPECT_EQ(8, custom::round_up(15,2));
}

TEST(conversion_test, u_t_t) {
    EXPECT_EQ(0, custom::uint_to_trit(0));
    EXPECT_EQ(16, custom::uint_to_trit(1));
    EXPECT_EQ(32, custom::uint_to_trit(2));
    EXPECT_EQ(48, custom::uint_to_trit(3));
}

TEST(conversion_test, t_t_u){
    EXPECT_EQ(0, custom::trit_to_uint(0));
    EXPECT_EQ(0, custom::trit_to_uint(12));

    EXPECT_EQ(1, custom::trit_to_uint(16));
    EXPECT_EQ(1, custom::trit_to_uint(25));

    EXPECT_EQ(2, custom::trit_to_uint(32));
    EXPECT_EQ(2, custom::trit_to_uint(33));
}

TEST_F(TritsetTest, capacity_test) {
    {
        custom::Tritset t1(1);
        ASSERT_EQ(16, t1.capacity());
    }
    {
        custom::Tritset t1(30);
        ASSERT_EQ(32, t1.capacity());
    }
    {
        custom::Tritset t1(0);
        ASSERT_EQ(0, t1.capacity());
    }
    {
        custom::Tritset t1(40);
        ASSERT_EQ(48, t1.capacity());
    }
}

TEST_F(TritsetTest, resize_test) {
    t1.resize(10);
    ASSERT_EQ(16,t1.capacity());
    t2.resize(17);
    ASSERT_EQ(32, t2.capacity());
    t3.resize(40);
    ASSERT_EQ(48, t3.capacity());
    t4.resize(0);
    ASSERT_EQ(0,t4.capacity());

}

TEST_F(TritsetTest, operator_brackes_test) {
    t1[10] = True;
    EXPECT_EQ(1, get_data(t1, 0));
}



/*int main() {

   return 0;
}*/
                    