import matplotlib.pyplot as plt
import random

TIME_PER_TASK = 45

def generate_random_color():
    """Generate a random color in hex format."""
    r = random.randint(128, 255)
    g = random.randint(128, 255)
    b = random.randint(128, 255)
    return "#{:02x}{:02x}{:02x}".format(r, g, b)

def render_schedule(filename):
    # Read the file and extract the schedule data
    with open(filename, 'r') as file:
        lines = file.readlines()

    times = []
    tasks = []
    task_colors = {}
    start_times = []
    end_times = []

    for line in lines:
        time_range, task_name = line.strip().split(" : ")
        start_time, end_time = time_range.split(" - ")
        start_times.append(start_time)
        end_times.append(end_time)
        times.append(time_range)
        tasks.append(task_name)

        # associate colors
        if task_name not in task_colors:
            task_colors[task_name] = generate_random_color()

    #calculate the position for each task and the gaps
    y_positions = []
    y_pos = 0
    last_end_time = None

    for start_time, end_time in zip(start_times, end_times):
        if last_end_time:
            #gap based on the difference in minutes between last end time and current start time
            last_end_hour, last_end_minute = map(int, last_end_time.split(":"))
            start_hour, start_minute = map(int, start_time.split(":"))
            gap = (start_hour * 60 + start_minute) - (last_end_hour * 60 + last_end_minute)
            y_pos -= gap / TIME_PER_TASK  # Adjust y_pos for the gap
        y_positions.append(y_pos)
        y_pos -= 1  # move to the next task position
        last_end_time = end_time


    # Define the figure and axis
    fig, ax = plt.subplots(figsize=(10, len(tasks) * 1))

    # Plot each task as a horizontal bar with the corresponding color
    for i, task in enumerate(tasks):
        ax.barh(y_positions[i], 1, left=0, height=0.5, align='center', color=task_colors[task])
        ax.text(0.5, y_positions[i], task, va='center', ha='center', color='black')

    # set y-ticks as times
    ax.set_yticks(y_positions)
    ax.set_yticklabels(times)

    # Remove x-axis
    ax.xaxis.set_visible(False)

    # Display the plot or save it as an image
    plt.title('Daily Schedule')
    plt.savefig('schedule_image.png')

# Call the function with the output file
render_schedule('schedule_output.txt')
