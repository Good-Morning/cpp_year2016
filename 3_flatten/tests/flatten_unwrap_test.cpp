//
// Created by eugene on 11.10.2017
//
#ifdef _GTEST

#include "flatten.h"

#include <thread>
#include <gtest/gtest.h>

TEST(flatten_unwrap, promise_caused) {
	Promise<Future<Future<Future<int>>>> promise3;
	Promise<Future<Future<int>>> promise2;
	Promise<Future<int>> promise1;
	Promise<int> promise0;
	Future<Future<Future<Future<int>>>> future = promise3.GetFuture();
	promise3.Set(promise2.GetFuture());
	promise2.Set(promise1.GetFuture());
	promise1.Set(promise0.GetFuture());
	promise0.Set(5);
	Future<int> normalized(Flatten(std::move(future)));
	ASSERT_EQ(normalized.Get(), 5);
}

TEST(flatten_unwrap, function_caused) {
	auto future = Future<int>([] {
		std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
		return 5;
	});
	ASSERT_FALSE(future.IsReady());
	ASSERT_EQ(future.Get(), 5);
}

TEST(flatten_unwrap, function_caused_void) {
	auto future = Future<void>([] {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		return;
	});
	ASSERT_FALSE(future.IsReady());
	future.Get();
}

TEST(flatten_unwrap, function_caused_wrappered) {
	Future<Future<int>> future([] {
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		return Future<int>([] { return 5; });
	});
	ASSERT_FALSE(future.IsReady());
	ASSERT_EQ(Flatten(std::move(future)).Get(), 5);
}

#endif // _GTEST
