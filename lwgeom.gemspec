Gem::Specification.new do |spec|
  spec.name          = "lwgeom"
  spec.version       = '0.2.2'
  spec.authors       = ["Yaroslav Nelin"]
  spec.email         = ["y.nelin@gmail.com"]

  spec.summary       = 'Ruby bindings for lwgeom library'
  spec.description   = 'With this gem you can call lwgeom methods from ruby'
  spec.homepage      = "http://cropio.com"
  spec.license       = "MIT"

  spec.files         = Dir['ext/**/*.c'] + Dir['ext/**/extconf.rb']
  spec.require_paths = ["ext/lwgeom"]

  spec.extensions << 'ext/lwgeom/extconf.rb'

  spec.add_development_dependency('test-unit')
  spec.add_development_dependency('rake')
end
