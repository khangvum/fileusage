# File Usage

A Windows console application that lists **_file usage_** by grouping files based on **_their extensions_**. This program counts the **_total_** number of files and calculates their cumulative **_sizes_**.

## Features

-   Lists **_files in a directory_** and **_groups them by their file extensions_**.
-   Displays the **_total number of files per extension_**.
-   Calculates the cumulative **_size of files for each extension_**.
-   Simple, fast, and lightweight **_console-based_** interface.

## Modern File Management with `<filesystem>`

For **_efficient_** and **_modern file management_**, the program utilizes the `<filesystem>` library, introduced in **_C++17_**. Compared to legacy and platform-specific methods (_e.g._ `FindFirstFile`, `FindNextFile` on Windows), which were often bulky and mistake-susceptible, this library introduces a **_standardized_**, **_cross-platform_**, and **_intuitive_** approach for handling files and directories.

-   **Cross-Platform Compatibility:** The `filesystem` library works seamlessly across **_Windows_**, **_Linux_**, and **_macOS_**, eliminating the need for platform-specific code.
-   **Ease of Use:** This library streamlines **_straightforward_** and **_high-level_** APIs for common operations like iterating directories, retrieving file sizes, and filtering files based on extensions.

    ```cpp
    for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
        if (entry.is_regular_file()) {
            auto size{ entry.file_size() };
        }
    }
    ```

-   **Performance:** Optimized for **_modern hardware_**, `filesystem` offers better performance compared to legacy implementations.
-   **Built-in Error Handling:** This modern approach automatically throws exceptions for **_invalid paths_**, **_permission issues_**, etc. simplifying error management.

## Performance Optimization with Thread Pooling

To improve the program's performance, a custom `ThreadPool` is used for **_concurrent execution_**. By utilizing **_multiple threads_**, the program can efficiently **_process files in parallel_**, significantly reducing execution time, especially when dealing with large directories containing numerous files (_e.g._ `C:\`).

-   **Parallel Task Execution:** The `ThreadPool` manages **_a pool of worker threads_** that handle tasks concurrently, ensuring **_faster file scanning_**.
-   **Efficient Resource Utilization:** The number of threads is determined based on the **_hardware's logical processors_**, maximizing CPU utilization without overwhelming the system.

    ```cpp
    size_t num_threads{ thread::hardware_concurrency() };
    ```

## Usage
  
<!-- <pre style="font-family: Consolas, monospace; font-size: 14px; background-color: #eee; padding: 15px; border: 1px solid #ccc; border-radius: 5px; white-space: pre; color: #333;"> -->

```
Usage: fileusage [--help] [-hdrsv(x regularexpression)] [folder]
switches:
        h       help
        d       reverse the order of listing
        r       suppress recursion
        s       sort by file sizes
        v       verbose
        b       benchmark
        x       filter with a regular expression

folder
        starting folder or current folder if not specified
```

<!-- </pre> -->

## Ignored Files

The following files are **_intentionally excluded_** from the repository:

-   scan_directory.cpp
-   ThreadPool.hpp/ThreadPool.cpp
-   benchmark.cpp

These files are excluded for **_personal_** and **_copyright_** reasons. If you need these files, please contact me via my email: [manhkhang0305@gmail.com](mailto:manhkhang0305@gmail.com)