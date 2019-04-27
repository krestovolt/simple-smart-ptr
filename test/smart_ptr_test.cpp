#include "dummy.h"
#include "smart_ptr.h"
#include "gtest/gtest.h"

TEST(SmartPtr, SmartPtr__should_be_able_construct_object_with_passed_ptr_params) {
	lib::SmartPtr<Dummy> s_ptr = lib::SmartPtr<::Dummy>(new ::Dummy(321));
	ASSERT_EQ(s_ptr->n, 321);

	s_ptr->n = 123;
	ASSERT_EQ(s_ptr->n, 123);
}

TEST(SmartPtr, SmartPtr__should_be_able_construct_object_with_empty_params) {
	lib::SmartPtr<::Dummy> s_ptr = lib::SmartPtr<::Dummy>();
	
	ASSERT_EQ(s_ptr->n, 0);

	s_ptr->n = 123;

	ASSERT_EQ(s_ptr->n, 123);
}


TEST(SmartPtr, SmartPtr__should_be_able_construct_object_with_deep_copy_constructor) {
	lib::SmartPtr<::Dummy> s_ptr = lib::SmartPtr<::Dummy>();
	lib::SmartPtr<::Dummy> s_ptr2 = lib::SmartPtr<::Dummy>(s_ptr);
	ASSERT_EQ(s_ptr->n, 0);
	ASSERT_EQ(s_ptr2->n, 0);
	
	s_ptr->n = 123;
	s_ptr2->n = 876;

	ASSERT_EQ(s_ptr->n, 123);
	ASSERT_EQ(s_ptr2->n, 876) << "shall not affected by the changes from the original copy";
}


TEST(SmartPtr, LifeSpan__different_scope_should_not_affect_each_copy) {
	lib::SmartPtr<::Dummy> s_ptr = lib::SmartPtr<::Dummy>();
	{
		lib::SmartPtr<::Dummy> s_ptr2 = lib::SmartPtr<::Dummy>(s_ptr);
		ASSERT_EQ(s_ptr2->n, 0);
		s_ptr2->n = 876;

		ASSERT_EQ(s_ptr->n, 0);	
		s_ptr->n = 123;

		ASSERT_EQ(s_ptr2->n, 876) << "shall not affected by the changes from the original copy";
	}
	
	ASSERT_EQ(s_ptr->n, 123);
}

TEST(SmartPtr, LifeSpan__should_not_deleted_when_any_reference_still_exist) {
	lib::SmartPtr<::Dummy> s_ptr;
	{
		lib::SmartPtr<::Dummy> s_ptr2 = lib::SmartPtr<::Dummy>();
		s_ptr = s_ptr2;
		ASSERT_EQ(s_ptr->n, 0);

		s_ptr2->n = 876;
		ASSERT_EQ(s_ptr2->n, s_ptr->n);
		
		s_ptr->n = 123;
		
		ASSERT_EQ(s_ptr2->n, s_ptr->n) << "shall affected by the changes from the original copy";
	}
	
	ASSERT_EQ(s_ptr->n, 123);
}


TEST(SmartPtr, LifeSpan__internal_data_pointers_should_be_deleted_when_there_is_no_ref_count_0) {
	lib::SmartPtr<::Dummy> s_ptr = lib::SmartPtr<::Dummy>();
	s_ptr->n = 123;	
	ASSERT_EQ(s_ptr->n, 123);

	s_ptr.~SmartPtr();
	ASSERT_EQ(s_ptr.ref(), nullptr);
	ASSERT_EQ(s_ptr.ptr(), nullptr);
	
}