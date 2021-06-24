#ifndef _CU_ARRAY_H_
#define _CU_ARRAY_H_

#include <stdexcept>
#include <algorithm>
#include <cuda_runtime.h>

template <class T>
class cu_array
{
	//Public functions
public:
	explicit cu_array()
		: start_(0),
		end_(0)
	{}

	//Constructor
	explicit cu_array(size_t size)
	{
		allocate(size);
	}

	//Destructor
	~cu_array()
	{
		free();
	}

	//Resize vectors
	void resize(size_t size)
	{
		free();
		allocate(size);
	}

	//Return size
	size_t getSize() const
	{
		return end_ - start_;
	}

	//Return data
	const T* getData() const
	{
		return start_;
	}

	T* getData()
	{
		return start_;
	}

	//Setter
	void set(const T* src, size_t size)
	{
		size_t min = std::min(size, getSize());
		cudaError_t result = cudaMemcpy(start_, src, min * sizeof(T), cudaMemcpyHostToDevice);
		if (result != cudaSuccess)
		{
			throw std::runtime_error("failed to copy host to memory");
		}
	}

	//Getter
	void get(const T* src, size_t size) //The size is not working
	{
		cout << "trying get" << endl;
		size_t min = std::min(size, getSize());
		cout << "parameters fine" << endl;
		cudaError_t result = cudaMemcpy(start_, src, min * sizeof(T), cudaMemcpyDeviceToHost);
		if (result != cudaSuccess)
		{
			throw std::runtime_error("failed to copy memory to host");
		}
	}


//Private
private:
	//Allocate device memory
	void allocate(size_t size)
	{
		cudaError_t result = cudaMalloc((void**)&start_, size * sizeof(T));
		if (result != cudaSuccess)
		{
			start_ = end_ = 0;
			throw std::runtime_error("failed to allocate device memory");
		}
		end_ = start_ + size;
	}

	//Free memory on the device
	void free()
	{
		if (start_ != 0)
		{
			cudaFree(start_);
			start_ = end_ = 0;
		}
	}
	T* start_;
	T* end_;

};

#endif