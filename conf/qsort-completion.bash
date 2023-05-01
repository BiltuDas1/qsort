# https://opensource.com/article/18/3/creating-bash-completion-script
_qsort_completions(){
    if [ ${#COMP_WORDS[@]} -eq "2" ]; then
        COMPREPLY=($(compgen -W "--help --version --edit-conf --thread" -- "${COMP_WORDS[1]}"))
    else
        if [[ ${COMP_WORDS[1]} == "--edit-conf" && ${#COMP_WORDS[@]} -eq "3" ]]; then
            COMPREPLY=($(compgen -W "cli" -- "${COMP_WORDS[2]}"))
        fi
        if [[ ${COMP_WORDS[1]} == "--thread" && ${#COMP_WORDS[@]} -eq "3" ]]; then
            for((i=1;i<=$(nproc);i++)); do
                thread[$i-1]=$i
            done
            show_thread=${thread[@]}
            COMPREPLY=($(compgen -W "$show_thread" -- "${COMP_WORDS[2]}"))
        fi
    fi
}

complete -F _qsort_completions qsort