import matplotlib.pyplot as plt

real_time = [7*60+34.004, 60+54.271, 52.215, 32.156, 27.619, 20.608, 15.979, 13.996, 12.031, 10.655, 9.825, 9.208, 8.017, 7.997, 7.401, 6.508, 6.201, 5.726, 5.372, 5.136, 5.109, 4.624, 4.489, 4.263, 4.346]
user_time = [7*60+32.457, 3*60+47.655, 2*60+35.695, 2*60 + 6.225, 60+56.782, 60+50.127, 60+45.007, 60+43.428, 60+ 29.736, 60+19.327, 60+13.572, 60+5.148, 60+0.234, 55.936, 51.995, 48.784, 45.741, 43.136, 40.813,38.842, 36.933, 35.207, 33.695, 32.339, 30.948]

threads = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]


plt.title("Sorting 1M integers with merge sort")

plt.plot(threads, real_time, "b", label='real time')
plt.plot(threads, user_time, "r", label='system time')

plt.xlabel("Threads")
plt.ylabel("Seconds")

plt.legend()

plt.show()
