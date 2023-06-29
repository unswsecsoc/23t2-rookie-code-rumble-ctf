# Tron

## Authors

- @GeorgeMuscat

## Category

- recon

## Description

Through advanced reconnaissance, we have discovered the ssh credentials to an officer's machine. Exploit these credentials to gain access to the machine and collect critical operations intelligence.

## Difficulty

- Easy

## Solution

<details>
<summary>Spoiler</summary>

### Idea

A common thing to check when enumerating a linux machine is the list of cron jobs.

### Walkthrough

We can run `crontab -l` to view our crontab:

```
officer@28854d3e7863:~$ crontab -l
@reboot exec /usr/bin/xtract
```

This shows a suspicious script. Running it gives the flag:

```
officer@28854d3e7863:~$ /usr/bin/xtract
BEGINNER{TrOn_m0re_LiKE_CrON_xdd}
```

### Flag

`BEGINNER{TrOn_m0re_LiKE_CrON_xdd}`

</details>
