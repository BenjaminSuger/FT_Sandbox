# ft_sandbox

A pedagogical sandbox repository for learning git workflows (branching, PRs, rebasing, conflicts) before tackling larger projects.

This is **not** a real production project — it's a teaching tool. The code is simple on purpose; what matters is the workflow and CI/CD pipeline.

## Quick Start

```bash
cp .env.example .env
make up
```

The application will connect to the database, create the schema, insert test players, and display a scoreboard.

## Running Tests

Unit tests (fast, no database required):
```bash
make test-unit
```

All tests (includes integration with real Postgres):
```bash
make test
```

## For podman users (École 42)

On 42 school machines, use podman instead of docker:

```bash
alias docker=podman
pip install podman-compose --break-system-packages
```

The `Makefile` automatically detects which is available and uses it.

## Next Steps

- Read `EXERCICES.md` for hands-on training scenarios
- Read `SETUP_REPO.md` to understand repository protection rules
- See `git log --graph --oneline --all` to visualize the branch structure
# Development branch
Added Elo system
Setup completed
Elo implementation details
WIP: rank function
