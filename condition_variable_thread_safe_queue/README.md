# Condition Variable
Condition variable allow thread to wait for a condition to fullfil without wasting resources.
Condition Variable is an optimization on the busy-wait pattern.

```
// Busy-Wait -- BAD

while(!shared_resource.empty())
{
    mutex.unlock();
    sleep(1);
    mutex.lock();
}
```


