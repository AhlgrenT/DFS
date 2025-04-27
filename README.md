# DFS
Distributed file system

# SW Architecture

## Client Master
- Client asks the master for metadata
- The master tells the client which slaves to talk to when r/w

## Client Slave
- When client knows which slave to talk to, talk to slave directly to r/w data blocks

## Master Slave
- Master monitors slaves (hearthbeats msgs, registration of joining/leaving slaves, replication control)
- Master assigns files/blocks to slaves and keep tracks of where file pieces live


