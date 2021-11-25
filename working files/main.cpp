#include "func.h"
#include "trit.h"


using namespace std;
using custom::Unknown;
using custom::True;
using custom::False;
using custom::Trit;
using custom::TritsetTest;
using custom::dec;



TEST(Round_test, equal) {
    EXPECT_EQ(3, custom::round_up(5,2));
    EXPECT_EQ(4, custom::round_up(10,3));
    EXPECT_EQ(7, custom::round_up(40,6));
    EXPECT_EQ(8, custom::round_up(15,2));
}

TEST(conversion_test, u_t_t) {
    EXPECT_EQ(0, custom::_trit(0));
    EXPECT_EQ(16, custom::_trit(1));
    EXPECT_EQ(32, custom::_trit(2));
    EXPECT_EQ(48, custom::_trit(3));
}

TEST(conversion_test, t_t_u){
    EXPECT_EQ(0, custom::_uint(0));
    EXPECT_EQ(0, custom::_uint(12));

    EXPECT_EQ(1, custom::_uint(16));
    EXPECT_EQ(1, custom::_uint(25));

    EXPECT_EQ(2, custom::_uint(32));
    EXPECT_EQ(2, custom::_uint(33));
}

TEST(conversion_test, b_t_d) {
    EXPECT_EQ(3, custom::dec(11));
    EXPECT_EQ(5, custom::dec(101));
    EXPECT_EQ(6, custom::dec(110));
    EXPECT_EQ(7, custom::dec(111));
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
    t1->resize(10);
    ASSERT_EQ(16,t1->capacity());
    t2->resize(17);
    ASSERT_EQ(32, t2->capacity());
    t3->resize(40);
    ASSERT_EQ(48, t3->capacity());
    t4->resize(0);
    ASSERT_EQ(0,t4->capacity());
}

TEST_F(TritsetTest, operator_brackes_test) {
    (*t1)[10] = True;
    EXPECT_EQ(1024, get_data(*t1, 0));
    (*t1)[0] = False;
    EXPECT_EQ(2147484672, get_data(*t1, 0));
    (*t1)[0] = Unknown;
    EXPECT_EQ(1024, get_data(*t1, 0));
    (*t1)[15] = True;
    EXPECT_EQ(1025, get_data(*t1, 0));

    (*t1)[10] = Unknown;
    ASSERT_EQ(16, t1->capacity());
}

TEST_F(TritsetTest, operator_as_test) {
    (*t1)[48] = False;
    *t2 = t1;
    ASSERT_EQ(t1->capacity(), t2->capacity());
    ASSERT_EQ((Trit)(*t1)[48], (Trit)(*t2)[48]);

    (*t3)[48] = Unknown;
    (*t3)[0] = True;
    *t4 = t3;
    ASSERT_EQ(t3->capacity(), t4->capacity());
    ASSERT_EQ((Trit)(*t3)[0], (Trit)(*t4)[0]);
}

TEST_F(TritsetTest, shirnk_test) {
    t1->resize(1000000);
    (*t1)[47] = False;
    t1->shrink();
    ASSERT_EQ(48, t1->capacity());

    t2->resize(1000000);
    (*t2)[48] = False;
    t2->shrink();
    ASSERT_EQ(64, t2->capacity());

    t3->resize(1000000);
    (*t3)[0] = True;
    t3->shrink();
    ASSERT_EQ(16, t3->capacity());
}


/*int main() {

   return 0;
}*/
                    