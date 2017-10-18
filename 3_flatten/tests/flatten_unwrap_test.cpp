//
// Created by eugene on 11.10.2017
//
#ifdef _GTEST

#include "CodeStyle.h"
#include "flatten.h"

#include <thread>
#include <gtest/gtest.h>

TEST(flatten_unwrap, promise_caused) {
	Promise<Future<Future<Future<int>>>> promise3;
	Promise<Future<Future<int>>> promise2;
	Promise<Future<int>> promise1;
	Promise<int> promise0;
	Future<Future<Future<Future<int>>>> future = promise3.GET_FUTURE();
	promise3.SET(promise2.GET_FUTURE());
	promise2.SET(promise1.GET_FUTURE());
	promise1.SET(promise0.GET_FUTURE());
	promise0.SET(5);
	Future<int> normalized(FLATTEN(std::move(future)));
	ASSERT_EQ(normalized.GET(), 5);
}

TEST(flatten_unwrap, function_caused) {
	auto future = Future<int>([] {
		std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
		return 5;
	});
	ASSERT_FALSE(future.IS_READY());
	ASSERT_EQ(future.GET(), 5);
}

TEST(flatten_unwrap, function_caused_void) {
	auto future = Future<void>([] {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		return;
	});
	ASSERT_FALSE(future.IS_READY());
	future.GET();
}

TEST(flatten_unwrap, function_caused_wrappered) {
	Future<Future<int>> future([] {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		return Future<int>([] { return 5; });
	});
	ASSERT_FALSE(future.IS_READY());
	ASSERT_EQ(FLATTEN(std::move(future)).GET(), 5);
}

#endif // _GTEST
