#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define N 1024

int main()
{
    cl_platform_id platform_id;
    cl_device_id device_id;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_mem a_mem, b_mem;
    cl_int err;

    // Create an array of numbers
    int a[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = i + 1;
    }

    // Get the first platform and device
    err = clGetPlatformIDs(1, &platform_id, NULL);
    err |= clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error getting platform or device.");
    }

    // Create a context
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &err);
    if (err != CL_SUCCESS)
    {
        printf("Error creating context.");
    }

    // Create a command queue
    queue = clCreateCommandQueue(context, device_id, 0, &err);
    if (err != CL_SUCCESS)
    {
        printf("Error creating command queue.");
    }

    // Create the program
    const char *source = "__kernel void sum(__global int* a, __global int* b) {"
                         "    int i = get_global_id(0);"
                         "    b[i] = a[i];"
                         "    for (int j = 0; j < i; j++) {"
                         "        b[i] += a[j];"
                         "    }"
                         "}";
    program = clCreateProgramWithSource(context, 1, &source, NULL, &err);
    if (err != CL_SUCCESS)
    {
        printf("Error creating program.");
    }

    // Build the program
    err = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error building program.");
    }

    // Create the kernel
    kernel = clCreateKernel(program, "sum", &err);
    if (err != CL_SUCCESS)
    {
        printf("Error creating kernel.");
    }

    // Create memory buffers
    b_mem = clCreateBuffer(context, CL_MEM_WRITE_ONLY, N * sizeof(int), NULL, &err);
    a_mem = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(int), a, &err);
    if (err != CL_SUCCESS)
    {
        printf("Error creating memory buffers.");
    }

    // Set kernel arguments
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &a_mem);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &b_mem);
    if (err != CL_SUCCESS)
    {
        printf("Error setting kernel arguments.");
    }

    // Execute the kernel
    size_t global_size = N;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, NULL, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error executing kernel.");
    }

    // Read the memory buffer

    // Read the memory buffer
    int b[N];
    err = clEnqueueReadBuffer(queue, b_mem, CL_TRUE, 0, N * sizeof(int), b, 0, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        printf("Error reading memory buffer.\n");
    }

    // Calculate the total sum and print the sum for each parallelism
    int total_sum = 0;
    for (int i = 0; i < N; i++)
    {
        total_sum += b[i];
        printf("Iteration %d: %d\n", i, b[i]);
    }
    printf("Total sum: %d\n", total_sum);

    // Clean up
    if (a_mem)
        clReleaseMemObject(a_mem);
    if (b_mem)
        clReleaseMemObject(b_mem);
    if (kernel)
        clReleaseKernel(kernel);
    if (program)
        clReleaseProgram(program);
    if (queue)
        clReleaseCommandQueue(queue);
    if (context)
        clReleaseContext(context);

    return 0;
}
