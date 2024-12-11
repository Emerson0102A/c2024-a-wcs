import time
import psutil
from mpmath import mp


mp.dps = 10010

def calculate_pi():
    return mp.pi

def memory_usage_psutil():
    process = psutil.Process()
    mem_info = process.memory_info()
    return mem_info.rss / 1024 / 1024  


start_time = time.perf_counter()
initial_memory = memory_usage_psutil()


memory_samples = [initial_memory]
for _ in range(10):  
    pi_value = calculate_pi()
    memory_samples.append(memory_usage_psutil())


end_time = time.perf_counter()
final_memory = memory_usage_psutil()


print(f"π (前50位)：{str(pi_value)[:10000]}...")
print(f"总时间：{end_time - start_time:.4f} 秒")
print(f"最大内存消耗：{max(memory_samples) - initial_memory:.2f} MB")
