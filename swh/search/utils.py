def stream_results(f, *args, **kwargs):
    if 'cursor' in kwargs:
        raise ArgumentError('stream_results has no argument "cursor".')
    cursor = None
    while True:
        results = f(*args, cursor=cursor, **kwargs)
        yield from results['results']
        cursor = results['cursor']
        if cursor is None:
            break
