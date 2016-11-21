# ~/.bashrc: executed by bash(1) for non-login shells.
# ~/.bashrc: 비로그인 쉘들은 bash(1)에 의해 실행된다.
#see /usr/share/doc/bash/examples/startup-files (in the package bash-doc) for examples
#예시를 통해 /usr/share/doc/bash/examples/startup-files을 봐라.(bash-doc 패키지 안에있는)

#If not running interactively, don't do anything
#만약에 대화식으로 작용하지 않는다면, 아무것도 하지 마라.

case $- in
*i*) ;;
  *) return;;
 esac

#don't put duplicate lines or lines starting with space in the history.
#히스토리안에 중복되는 라인 또는 공백으로 시작하는 라인을 두지 마라.
#See bash(1) for more options
#더 많은 옵션의 있는 bash(1)을 봐라.

HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
#히스토리 파일을 첨부하라. 중복기재는 하지 말아라.

shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
#히스토리 길이를 설정하기 위해서 bash(1)의 HISTSIZE, HISTFILESIZE를 봐라.

HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
#각각의 명령 후 window사이즈를 확인하고 만약 팔요하다면,
#  update the values of LINES and COLUMNS.
#행과 열의 값을 업데이트해라.

shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
#만약 설정했다면, pathname 확장 문맥에 사용된 패턴 "**"은
# match all files and zero or more directories and subdirectories.
#모든 파일들과 0 또는 더 많은 디렉토리와 서브디렉토리들이 일치할 것이다.

shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
#non-text 입력 파일들에 대하여 less를 더욱더 친근하게 만들라, lesspipe(1)을 봐라.

[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
#작업을 하고 있는 chroot을 감별할 수 있는 변수를 설정하라.(prompt에서 사용되는)

if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
debian_chroot=$(cat /etc/debian_chroot)

fi

# set a fancy prompt (non-color, unless we know we "want" color)
#복잡한 prompt를 설정하라.(만약 우리가 "원한다" 색깔을 알지 못한다면, 색깔은 없다)

case "$TERM" in
xterm-color) color_prompt=yes;;
esac

# uncomment(주석처리 제거) for a colored prompt, if the terminal has the capability; 
#만약 터미널이 이용가능하다면, 색있는 prompt에 대하여 주석처리를 제거한다.
#turned off by default to not distract the user: 
#사용자가 집중을 할 수 있도록 디폴트를 끊어라.
#the focus in a terminal window should be on the output of commands, not on the prompt
#터미널창에서의 초점은 명령어의 결과물이 있어야만 한다. prompt가 아닌

 force_color_prompt=yes

 if [ -n "$force_color_prompt" ]; then
   if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
 # We have color support; assume it's compliant with Ecma-48
 #우리는 색깔 지원을 가지고 있다; 이것은 E-cma-48에 준수한다고 가정하자.
 # (ISO/IEC-6429). (Lack of such support is extremely rare, and such
 #(ISO/IEC-6429).(이러힌 지원의 부족은 극히 드물다. 그리고
 # a case would tend to support setf rather than setaf.)
 #이러한 경우는 setaf보다 오히려 setf를 지지하는 경향이 있다.)
   color_prompt=yes

 else
   color_prompt=
  fi
fi

if [ "$color_prompt" = yes ]; then
  PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
#만약 이것이 xterm이라면 제목을 user@host:dir로 설정하라.

case "$TERM" in
xterm*|rxvt*)
PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
;;
*)
;;
esac

# enable color support of ls and also add handy aliases
#ls의 색끼리 가능하게 하고 유용한 명령어를 추가하라.

if [ -x /usr/bin/dircolors ]; then
test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval    "$(dircolors -b)"
alias ls='ls --color=auto'
#alias dir='dir --color=auto'
#alias vdir='vdir --color=auto'

alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'
fi

# some more ls aliases
#더 많은 ls 명령어들
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# Add an "alert" alias for long running commands.  Use like so:
#긴 실행시간 명령어를 위해 "alert"명령어를 추가해라. 다음과 같이 사용:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
#명령어 정의
# You may want to put all your additions into a separate file like
#너는 너의 다음과 같은 ~/.bash_aliases, instead of adding them here directly. 분리된 파일에
#추가사항들을 넣기를 원할지도 모른다.
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.
#bash-doc패키지 안에 /usr/share/doc/bash-doc/examples을 봐라.

if [ -f ~/.bash_aliases ]; then
. ~/.bash_aliases
fi

if [ -f ~/.local/lib/python2.7/site-packages/powerline/bindings  /bash/powerline.sh ]; then
source ~/.local/lib/python2.7/site-packages/powerline/bindings/bash/powerline.sh
fi


# enable programmable completion features (you don't need to enable
#사용가능하고 프로그램작동이 가능한 특징(너가 이러한 것을 필요로 하지 않는다.
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
#만약 이것이 etc/bash.bashrc and /etc/profilesources /etc/bash.bashrc)에서 이미 가능하다면)
# sources /etc/bash.bashrc).

if ! shopt -oq posix; then
 if [ -f /usr/share/bash-completion/bash_completion ]; then
. /usr/share/bash-completion/bash_completion
elif [ -f /etc/bash_completion ]; then
. /etc/bash_completion
  fi
fi
[ -f ~/.fzf.bash ] && source ~/.fzf.bash
