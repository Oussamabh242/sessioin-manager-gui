# sessioin-manager

`sessionctl` is a GTK-based application for managing common system actions such as logging out, locking the screen, shutting down, and restarting your system. It provides a graphical interface to confirm these actions before executing them.

## Features

- **Logout**: Exit the current session.
- **Lock Screen**: Lock the screen using `i3lock`.
- **Shutdown**: Shut down the system.
- **Restart**: Restart the system.

## Prerequisites

- **GTK+ 3**: The application requires GTK+ 3 libraries to compile and run.
- **i3lock**: For the lock screen functionality.
- **i3-msg**: For logging out from the i3 window manager.

## Installation

1. **Clone the Repository**

```bash
git clone https://github.com/yourusername/sessionctl.git
cd sessionctl
```

2. **install Dependencies**

Ensure you have GTK+ 3 and i3lock installed. On Debian-based systems, you can install them with:

```bash
sudo apt-get install libgtk-3-dev i3lock
```

3. **Compile the Application**

```bash
gcc $(pkg-config --cflags gtk4) -o sessionctl main.c $(pkg-config --libs gtk4)
```

4. **Install (Optional)**

To install the application system-wide:

```bash
sudo cp sessionctl /usr/local/bin/
```

## Usage
Run the application from the terminal or a launcher:

```bash
sessionctl
```
The application will display a window with buttons for each action. Clicking on a button will open a confirmation dialog. Clicking "Yes" will execute the selected action, while "No" will close the confirmation dialog.

