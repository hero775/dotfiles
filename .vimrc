" let g:solarized_termcolors = 16

set autoindent
set cindent
set nu
set cursorline
if exists("&relativenumber")
	set relativenumber
	au BufReadPost * set relativenumber
endif


set ts=4 "Tab 너비
set sw=4 "자동 인덴트할 때 너비

" Vundle 설치코드
set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')
" let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'
Plugin 'christoomey/vim-tmux-navigator'
Plugin 'The-NERD-Tree'
Plugin 'AutoComplPop'
Plugin 'taglist-plus'
" 2019.07.28 Setting Theme
Plugin 'altercation/vim-colors-solarized'
Plugin 'digitaltoad/vim-pug'
call vundle#end()            " required

filetype plugin indent on    " required
" 2019.07.28 Setting Theme
syntax enable
set background=dark
colorscheme solarized
"colorscheme jellybeans


map <F9> :NERDTreeToggle<CR>
map <C-h> <C-w>h
map <C-j> <C-w>j
map <C-l> <C-w>l
map <C-F> :NERDTreeFind<CR>

let g:tmux_navigator_no_mappings = 1
nnoremap <silent> <C-j> :TmuxNavigateDown<cr>
nnoremap <silent> <C-k> :TmuxNavigateUp<cr>

set rtp+=/usr/local/lib/python2.7/dist-packages/powerline/bindings/vim/

let mapleader=","
nnoremap <Leader>rc :rightbelow vnew $MYVIMRC<CR>
nnoremap <Leader>n :NERDTreeToggle<CR>
nnoremap <C-F> :NERDTreeFind<CR>


map <C-h> <C-w>h
map <C-l> <C-w>l
map <C-j> <C-w>j
map <C-k> <C-w>k
nnoremap <silent> <C-h> :TmuxNavigateLeft<cr>
nnoremap <silent> <C-l> :TmuxNavigateRight<cr>
nnoremap <silent> <C-j> :TmuxNavigateDown<cr>
nnoremap <silent> <C-k> :TmuxNavigateUp<cr>

"nnoremap <C-y> <C-w>h
"nnoremap <C-u> <C-w>j
"nnoremap <C-i> <C-w>k
"nnoremap <C-o> <C-w>l

" Folding
map <F1> v]}zf
map <F2> zo



imap <C-D> <C-R>=strftime("%Y.%m.%d - %H:%M:%S")<CR>


" ESC 딜레이 없애기
set ttimeout
set ttimeoutlen=100
set timeoutlen=3000

set clipboard=unnamed " use OS clipboard 
"set clipboard=unnamedplus
