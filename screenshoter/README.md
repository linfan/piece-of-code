HTML Screenshot Demo
---

# Run script
```bash
python screenshot.py file:///path/to/demo.html demo.png
```

# Build docker image

```bash
docker build -t screenshoter .
```

```bash
docker run --rm -it -v /path/to/html:/html screenshoter file:///html/demo.html /html/demo.png
```
