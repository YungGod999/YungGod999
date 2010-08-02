#pragma once

const size_t BIAS_INPUT = 1;
const double BIAS_VALUE = 1.0;

template<class Iterator1, class Iterator2, class Functor>
void ForEach2It(Iterator1 first1, Iterator1 last1
	, Iterator2 first2
	, Functor functor)
{
	for(; first1!=last1; ++first1, ++first2)
		functor(*first1, *first2);
}

template<class Iterator1, class Iterator2, class Iterator3, class Functor>
void ForEach3It(Iterator1 first1, Iterator1 last1
	, Iterator2 first2
	, Iterator3 first3
	, Functor functor)
{
	for(; first1!=last1; ++first1, ++first2, ++first3)
		functor(*first1, *first2, *first3);
}
