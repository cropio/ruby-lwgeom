# Ruby-LwGeom
[![Build Status](https://travis-ci.org/cropio/ruby-lwgeom.svg?branch=master)](https://travis-ci.org/cropio/ruby-lwgeom)

A set of bindings between Ruby and LwGeom library

## Requirements
* LwGeom

## Installation
If you have checked out this local repository code build like:

```
ruby /ext/lwgeom/extconf.rb
make
gem build lwgeom.gemspec
gem install lwgeom
```

or you can add this line to your application's Gemfile
```ruby
gem 'lwgeom'
```

And then execute
```
bundle
```

## Contributing
1. Fork it ( https://github.com/cropio/ruby-lwgeom/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request