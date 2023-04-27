# https://opensource.com/article/18/3/creating-bash-completion-script
_qsort_completions(){
    if [ ${#COMP_WORDS[@]} -eq "2" ]; then
        COMPREPLY=($(compgen -W "--help --version --edit-conf" -- "${COMP_WORDS[1]}"))
    else
        if [[ ${COMP_WORDS[1]} == "--edit-conf" && ${#COMP_WORDS[@]} -eq "3" ]]; then
            COMPREPLY=($(compgen -W "cli" -- "${COMP_WORDS[2]}"))
        fi
    fi
}

complete -F _qsort_completions qsort