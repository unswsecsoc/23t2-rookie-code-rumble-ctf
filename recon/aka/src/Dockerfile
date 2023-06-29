FROM ubuntu:latest

# Need ssh cause im not setting up a nc connection
RUN apt update && apt install openssh-server cron -y

# Change root user password so changes can be made on the fly
RUN echo "root:m0re_smart_m0rt3in" | chpasswd

# Create a user and group (alien warfare theme...)
RUN groupadd officer && useradd -ms /bin/bash -g officer officer

# Create ssh user account directory in home
RUN mkdir -p /home/officer/.ssh

# Create sus script
RUN echo "#!/bin/bash\n\necho QkVHSU5ORVJ7VHJPbl9tMHJlX0xpS0VfQ3JPTl94ZGR9Cg== | base64 -d" > /usr/bin/xtract

# Make it executable for all
RUN chmod 755 /usr/bin/xtract

# Create crontab to run sussy script
RUN { crontab -l -u officer; echo '@reboot	exec /usr/bin/xtract'; } | crontab -u officer -

# Change the password to a preset value
RUN echo officer:iCANTstandROOKIES1337 | chpasswd

# Create the aliases in a spot that is not expected for a beginner (not .bashrc) and base64 so no greping
RUN echo "#!/bin/bash\n\nalias woop='echo QkVHSU5ORVJ7c1VwRXJfRmFzVF9hTmRfRWFTeV9BbGlBc2VzX3cwMHAhfQo= | base64 -d'" > /etc/profile.d/00-aka.sh

# Create .hushlogin to prevent default MOTD
RUN touch /home/officer/.hushlogin

# Create own jank MOTD in .bashrc (This should be the easiest flag)
RUN echo "echo BEGINNER{SeCReT_OfFiCeR_MoTD_2359fabe}; sleep 1; clear;" >> /home/officer/.bashrc

# No writing here!!!!
RUN chmod -R 0555 /home/officer

# Start SSH service
RUN service ssh start

# Expose docker port 22
EXPOSE 22
CMD ["/usr/sbin/sshd","-D"]
