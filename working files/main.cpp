#include "func.h"
#include "trit.h"
#include <iostream>
#include <gtest/gtest.h>


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
    *t2 = *t1;
    ASSERT_EQ(t1->capacity(), t2->capacity());
    ASSERT_EQ((Trit)(*t1)[48], (Trit)(*t2)[48]);

    (*t3)[48] = Unknown;
    (*t3)[0] = True;
    *t4 = *t3;
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

TEST(op_test, _and_) {
    EXPECT_EQ(False, custom::_and(False, False));
    EXPECT_EQ(False, custom::_and(False, Unknown));
    EXPECT_EQ(False, custom::_and(False, True));
    EXPECT_EQ(Unknown, custom::_and(Unknown, Unknown));
    EXPECT_EQ(Unknown, custom::_and(Unknown, True));
    EXPECT_EQ(True, custom::_and(True, True));
}

TEST(op_test, _or_) {
    EXPECT_EQ(False, custom::_or(False, False));
    EXPECT_EQ(Unknown, custom::_or(False, Unknown));
    EXPECT_EQ(True, custom::_or(False, True));
    EXPECT_EQ(Unknown, custom::_or(Unknown, Unknown));
    EXPECT_EQ(True, custom::_or(Unknown, True));
    EXPECT_EQ(True, custom::_or(True, True));
}

TEST(op_test, _not) {
    EXPECT_EQ(False, custom::_not(True));
    EXPECT_EQ(True, custom::_not(False));
    EXPECT_EQ(Unknown, custom::_not(Unknown));
}

TEST_F(TritsetTest, and_test) {
    (*t1)[31] = True;
    (*t2)[31] = Unknown;
    *t3 = *t1 & *t2;
    EXPECT_EQ(Unknown, (Trit)(*t3)[31]);
}

TEST_F(TritsetTest, or_test) {
    (*t1)[31] = True;
    (*t2)[31] = Unknown;
    *t3 = *t1 | *t2;
    EXPECT_EQ(True, (Trit)(*t3)[31]);
}

TEST_F(TritsetTest, not_test) {
    (*t1)[16] = True;
    *t2 = ~(*t1);
    EXPECT_EQ(False, (Trit)(*t2)[16]);

    (*t1)[66] = False;
    *t1 = ~(*t1);
    EXPECT_EQ(True, (Trit)(*t1)[66]);

    (*t1)[66] = Unknown;
    *t1 = ~(*t1);
    EXPECT_EQ(Unknown, (Trit)(*t1)[66]);
}

TEST_F(TritsetTest, cardinality_test) {
    t1->resize(64);
    EXPECT_EQ(64, t1->cardinality(Unknown));

    (*t1)[31] = True;
    (*t1)[35] = True;
    (*t1)[40] = True;
    (*t1)[51] = True;
    (*t1)[61] = True;
    EXPECT_EQ(5, t1->cardinality(True));
    EXPECT_EQ(57, t1->cardinality(Unknown));

    (*t1)[30] = False;
    (*t1)[32] = False;
    (*t1)[43] = False;
    (*t1)[52] = False;
    EXPECT_EQ(4, t1->cardinality(False));
    EXPECT_EQ(53, t1->cardinality(Unknown));

    auto res = t1->cardinality();
    EXPECT_EQ(4, res[False]);
    EXPECT_EQ(5, res[True]);
    EXPECT_EQ(55, res[Unknown]);

}

TEST_F(TritsetTest, trim_test) {
    t1->resize(65);
    (*t1)[63] = False;
    t1->trim(63);
    EXPECT_EQ(64, t1->capacity());
    EXPECT_EQ(Unknown, (Trit)(*t1)[63]);
}

TEST_F(TritsetTest, length_test) {
    (*t1)[630] = False;
    EXPECT_EQ(631, t1->length());

    (*t2)[900] = True;
    EXPECT_EQ(901, t2->length());
}

TEST_F(TritsetTest, iterator_test) {
    t1->resize(10);
    for (auto trit: *t1) trit = True;

    for (auto  trit: *t1) ASSERT_EQ(trit, True);
}

TEST_F(TritsetTest, const_brackets) {
    const custom::Tritset T(100);

    Trit t = T[10];
    EXPECT_EQ(t, Unknown);
}