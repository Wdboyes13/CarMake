/*
CarMake - A simple build system using TOML
Copyright (C) 2025  Wdboyes13

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <git2.h>
#include <stdio.h>
#include <string.h>

#define INDEX rep.index
#define REPO rep.repo

struct repo{
    git_repository* repo;
    git_index* index;
};

struct repo getrepo(){
    struct repo rep;
    rep.repo = NULL;
    rep.index = NULL;

    if (git_repository_open(&rep.repo, ".") != 0) {
        fprintf(stderr, "Failed to open repo\n");
        return rep;
    }

    if (git_repository_index(&rep.index, rep.repo) != 0) {
        fprintf(stderr, "Failed to get index\n");
        git_repository_free(rep.repo);
        rep.repo = NULL;
        return rep;
    }

    return rep;
}

void gitinit(){
    git_libgit2_init();
}

void stageall(){
    
    struct repo rep = getrepo();

    if (rep.index == NULL || rep.repo == NULL) {
        fprintf(stderr, "Error: repo or index is NULL\n");
        return;
    }

    int err;
    err = git_index_add_all(rep.index, NULL, 0, NULL, NULL);
    if (err < 0) {
        const git_error *e = git_error_last();
        fprintf(stderr, "git_index_add_all failed: %s\n", e ? e->message : "unknown error");
    }

    err = git_index_write(rep.index);
    if (err < 0) {
        const git_error *e = git_error_last();
        fprintf(stderr, "git_index_write failed: %s\n", e ? e->message : "unknown error");
    }

    git_index_free(rep.index);
    git_repository_free(rep.repo);

}

void commit(char* name, char* email, char* commitmsg){
    struct repo rep = getrepo();
    git_oid tree_id, commit_id;
    git_tree *tree;
    git_signature *sig;
    git_oid parent_commit_id;
    git_commit *parent_commit = NULL;

    git_index_write_tree(&tree_id, INDEX);
    git_tree_lookup(&tree, REPO, &tree_id);

    git_signature_now(&sig, name, email);

    git_reference *headref = NULL;
    if (git_reference_lookup(&headref, REPO, "HEAD") == 0) {
        git_reference_name_to_id(&parent_commit_id, REPO, "HEAD");
        git_commit_lookup(&parent_commit, REPO, &parent_commit_id);
    }

    git_commit_create_v(
        &commit_id,
        REPO,
        "HEAD",
        sig, sig,
        NULL,
        commitmsg,
        tree,
        parent_commit ? 1 : 0,
        parent_commit ? (const git_commit **)&parent_commit : NULL
    );

    git_signature_free(sig);
    git_tree_free(tree);
    git_index_free(INDEX);
    git_repository_free(REPO);
}

void pushmain(char* remname, char* locname){
    struct repo rep = getrepo();

    git_remote *remote = NULL;
    git_push_options push_opts;

    git_remote_lookup(&remote, REPO, remname);
    git_push_options_init(&push_opts, GIT_PUSH_OPTIONS_VERSION);

    char* refstr = malloc(sizeof(char) * ((strlen(locname)*2)+30));
    sprintf(refstr, "refs/heads/%s:refs/heads/%s", locname, locname);
    const char *refspec = strdup(refstr);
    const git_strarray refspecs = {(char **)&refspec, 1};

    git_remote_push(remote, &refspecs, &push_opts);
    git_remote_free(remote);

    git_index_free(INDEX);
    git_repository_free(REPO);
}

void gitclean(){
    git_libgit2_shutdown();
}