from setuptools import setup

package_name = 'pantemaskin'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    install_requires=['setuptools'],
    zip_safe=True,
    entry_points={
        'console_scripts': [
            'arduino_node = pantemaskin.arduino_node:main',
        ],
    },
)
