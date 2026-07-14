FROM debian:bookworm as builder

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    libpqxx-dev \
    postgresql-client \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build

FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    libpqxx6 \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -u 1000 app && \
    mkdir -p /app && \
    chown -R app:app /app

WORKDIR /app
COPY --from=builder /build/ft_sandbox .

USER app

CMD ["./ft_sandbox"]
