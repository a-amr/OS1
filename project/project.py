import tkinter as tk
from tkinter import messagebox
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def priority():
    process_list = []
    num_processes = int(num_processes_entry.get())
    for i in range(num_processes):
        priority_num = int(priority_entries[i].get())
        process_name = process_name_entries[i].get()
        burst_time = int(burst_time_entries[i].get())
        arrival_time = int(arrival_time_entries[i].get())
        process_list.append([priority_num, process_name, burst_time, arrival_time])

    gnatt = []
    completed = {}
    t = 0  # Initialize time
    while process_list != []:
        available = []
        for p in process_list:
            arrival_time = p[3]
            if arrival_time <= t:
                available.append(p)

        if available == []:
            gnatt.append(("idle", t, t + 1))  # Add idle time to Gantt chart
            t += 1
            continue
        else:
            available.sort(key=lambda x: x[0])  # Sort based on priority
            process = available[0]
            process_list.remove(process)
            pid = process[1]
            gnatt.append((pid, t, t + process[2]))  # Add process to Gantt chart
            burst_time = process[2]
            t += burst_time
            ct = t
            arrival_time = process[3]
            tt = ct - arrival_time
            wt = tt - burst_time
            completed[pid] = [ct, tt, wt]

    output_text.delete(1.0, tk.END)
    output_text.insert(tk.END, "Process ID | Completion Time | Turnaround Time | Waiting Time | Response Time\n")
    output_text.insert(tk.END, "-" * 78 + "\n")
    avg_tt = 0
    avg_wt = 0
    avg_rt = 0
    for pid, stats in sorted(completed.items(), key=lambda x: x[0]):
        ct, tt, wt = stats
        rt = wt  # Assuming response time is the same as waiting time
        output_text.insert(tk.END, f"     {pid}      |        {ct}        |        {tt}        |      {wt}       |      {rt}       \n")
        avg_tt += tt
        avg_wt += wt
        avg_rt += rt

    avg_tt /= len(completed)
    avg_wt /= len(completed)
    avg_rt /= len(completed)
    output_text.insert(tk.END, f"\nAverage turnaround time: {avg_tt}\n")
    output_text.insert(tk.END, f"Average waiting time: {avg_wt}\n")
    output_text.insert(tk.END, f"Average response time: {avg_rt}\n")

    # Plot Gantt chart
    fig, ax = plt.subplots(figsize=(15,2))
    for i in range(len(gnatt)):
        if gnatt[i][0] != "idle":
            ax.broken_barh([(gnatt[i][1], gnatt[i][2] - gnatt[i][1])], (10, 9), facecolors='tab:blue')
            ax.text(gnatt[i][1] + 0.5, 14, gnatt[i][0], color='white', fontweight='bold', fontsize=8, ha='center')
        else:
            ax.broken_barh([(gnatt[i][1], gnatt[i][2] - gnatt[i][1])], (10, 9), facecolors='tab:red')
    ax.set_ylim(5, 20)
    ax.set_xlim(0, t)
    ax.set_xlabel('Time')
    ax.set_yticks([15])
    ax.set_yticklabels(['Processes'])
    ax.grid(True)

    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.draw()
    canvas.get_tk_widget().grid(row=3, column=0, columnspan=4, padx=5, pady=5)

root = tk.Tk()
root.title("Priority Scheduler")

num_processes_label = tk.Label(root, text="Enter the number of processes:")
num_processes_label.grid(row=0, column=0, padx=5, pady=5)

num_processes_entry = tk.Entry(root)
num_processes_entry.grid(row=0, column=1, padx=5, pady=5)

submit_button = tk.Button(root, text="Submit", command=priority)
submit_button.grid(row=0, column=2, padx=5, pady=5)

process_inputs_frame = tk.Frame(root)
process_inputs_frame.grid(row=1, column=0, columnspan=3, padx=5, pady=5)

priority_entries = []
process_name_entries = []
burst_time_entries = []
arrival_time_entries = []

def create_process_fields():
    num_processes = int(num_processes_entry.get())
    for i in range(num_processes):
        priority_label = tk.Label(process_inputs_frame, text=f"Priority for process {i+1}:")
        priority_label.grid(row=i, column=0, padx=5, pady=5)

        priority_entry = tk.Entry(process_inputs_frame)
        priority_entry.grid(row=i, column=1, padx=5, pady=5)
        priority_entries.append(priority_entry)

        process_name_label = tk.Label(process_inputs_frame, text=f"Name for process {i+1}:")
        process_name_label.grid(row=i, column=2, padx=5, pady=5)

        process_name_entry = tk.Entry(process_inputs_frame)
        process_name_entry.grid(row=i, column=3, padx=5, pady=5)
        process_name_entries.append(process_name_entry)

        burst_time_label = tk.Label(process_inputs_frame, text=f"Burst time for process {i+1}:")
        burst_time_label.grid(row=i, column=4, padx=5, pady=5)

        burst_time_entry = tk.Entry(process_inputs_frame)
        burst_time_entry.grid(row=i, column=5, padx=5, pady=5)
        burst_time_entries.append(burst_time_entry)

        arrival_time_label = tk.Label(process_inputs_frame, text=f"Arrival time for process {i+1}:")
        arrival_time_label.grid(row=i, column=6, padx=5, pady=5)

        arrival_time_entry = tk.Entry(process_inputs_frame)
        arrival_time_entry.grid(row=i, column=7, padx=5, pady=5)
        arrival_time_entries.append(arrival_time_entry)

create_process_fields_button = tk.Button(root, text="Create Process Fields", command=create_process_fields)
create_process_fields_button.grid(row=0, column=3, padx=5, pady=5)

output_text = tk.Text(root, height=15, width=100)
output_text.grid(row=2, column=0, columnspan=4, padx=5, pady=5)

root.mainloop()
